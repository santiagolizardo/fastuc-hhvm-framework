<?hh // strict
namespace Fastuc\Seo;

/**
 * This class creates XML sitemap index.
 */
class SitemapIndex
{
	/**
	 * @var array
	 */
	private array $sitemaps;

	public function __construct()
	{
		$this->sitemaps = array();
	}

	/**
	 * @param string $location
	 */
	public function addSitemap( string $location ) : void
	{
		$this->sitemaps[] = array( 'location' => $location );
	}

	/**
	 * @return array
	 */
	public function getSitemaps() : array
	{
		return $this->sitemaps;
	}

	/**
	 * @return string
	 */
	public function dumpToString() : string
	{
		$doc = new \DomDocument( '1.0', 'utf-8' );

		$sitemapindexNode = $doc->createElement( 'sitemapindex' );
		$sitemapindexNode->setAttribute( 'xmlns', 'http://www.sitemaps.org/schemas/sitemap/0.9' );
		$sitemapindexNode->setAttribute( 'xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance' );
		$sitemapindexNode->setAttribute( 'xsi:schemaLocation', 'http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd' );

		foreach( $this->sitemaps as $sitemap )
		{
			$sitemapNode = $doc->createElement( 'sitemap' );
			$sitemapNode->appendChild( $doc->createElement( 'loc', $sitemap['location'] ) );
			$sitemapindexNode->appendChild( $sitemapNode );
		}

		$doc->appendChild( $sitemapindexNode );
		
		return $doc->saveXml();
	}

	/**
	 * @return string
	 */
	public function __toString() : string
	{
		return sprintf( '[ SitemapIndex: sitemaps(%d) ]', count( $this->sitemaps ) );
	}
}

