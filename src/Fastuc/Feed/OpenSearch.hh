<?hh // strict
namespace Fastuc\Feed;

class OpenSearch
{
	/**
	 * @var string
	 */
	private string $name;

	/**
	 * @var string
	 */
	private string $description;

	/**
	 * @var string
	 */
	private string $imageUrl;

	/**
	 * @var string
	 */
	private string $searchUrl;

	/**
	 * @var string
	 */
	private string $searchMethod;

	/**
	 * @var string
	 */
	private string $searchParam;

	/**
	 * @param string $name
	 */
	public function __construct( string $name )
	{
		$this->name = $name;

		$this->searchMethod = 'post';
		$this->searchParam = 'query';
	}

	/**
	 * @param string $searchUrl
	 */
	public function setSearchUrl( string $searchUrl ) : void
	{
		$this->searchUrl = $searchUrl;
	}

	/**
	 * @param string $searchParam
	 */
	public function setSearchParam( string $searchParam ) : void
	{
		$this->searchParam = $searchParam;
	}

	/**
	 * @param string $description
	 */
	public function setDescription( string $description ) : void
	{
		$this->description = $description;
	}

	/**
	 * @param string $imageUrl
	 */
	public function setImageUrl( string $imageUrl ) : void
	{
		$this->imageUrl = $imageUrl;
	}

	/**
	 * @return string
	 */
	public function toXml() : string
	{
		$doc = new \DomDocument( '1.0', 'utf-8' );

		$osd = $doc->createElement( 'OpenSearchDescription' );
		$osd->setAttribute( 'xmlns', 'http://a9.com/-/spec/opensearch/1.1/' );
		$doc->appendChild( $osd );

		$shortName = $doc->createElement( 'ShortName' );
		$shortName->appendChild( $doc->createTextNode( $this->name ) );
		$osd->appendChild( $shortName );

		$description = $doc->createElement( 'Description' );
		$description->appendChild( $doc->createTextNode( $this->description ) );
		$osd->appendChild( $description );

		$inputEncoding = $doc->createElement( 'InputEncoding' );
		$inputEncoding->appendChild( $doc->createTextNode( 'utf-8' ) );
		$osd->appendChild( $inputEncoding );

		$image = $doc->createElement( 'Image' );
		$image->setAttribute( 'width', 16 );
		$image->setAttribute( 'height', 16 );
		$image->setAttribute( 'type', 'image/x-icon' );
		$image->appendChild( $doc->createTextNode( $this->imageUrl ) );
		$osd->appendChild( $image );

		$url = $doc->createElement( 'Url' );
		$url->setAttribute( 'type', 'text/html' );
		$url->setAttribute( 'method', $this->searchMethod );
		$url->setAttribute( 'template', $this->searchUrl );

		$param = $doc->createElement( 'Param' );
		$param->setAttribute( 'name', $this->searchParam );
		$param->setAttribute( 'value', '{searchTerms}' );
		$url->appendChild( $param );

		$osd->appendChild( $url );

		return $doc->saveXml();
	}
}

