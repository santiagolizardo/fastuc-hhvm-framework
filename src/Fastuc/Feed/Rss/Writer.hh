<?hh // strict
namespace Fastuc\Feed\Rss;

class Writer
{
	/**
	 * @var string
	 */
	private string $title;

	/**
	 * @var string
	 */
	private string $link;

	/**
	 * @var string
	 */
	private string $description;

	private Vector<Item> $items;

	public function __construct()
	{
		$this->items = new Vector<Item>;
	}

	/**
	 * @param string $title
	 */
	public function setTitle( string $title ) : void
	{
		$this->title = $title;
	}

	/**
	 * @param string $link
	 */
	public function setLink( string $link ) : void
	{
		$this->link = $link;
	}

	/**
	 * @param string $description
	 */
	public function setDescription( string $description ) : void
	{
		$this->description = $description;
	}

	public function addItem( Item $item ) : void
	{
		$this->items->add( $item );
	}

	/**
	 * @return string
	 */
	public function toXml() : string
	{
		$doc = new \DomDocument( '1.0', 'utf-8' );

		$rss = $doc->createElement( 'rss' );
		$rss->setAttribute( 'version', '2.0' );
		$doc->appendChild( $rss );

		$channel = $doc->createElement( 'channel' );
		$rss->appendChild( $channel );

		if( !empty( $this->title ) )
		{
			$title = $doc->createElement( 'title' );
			$title->appendChild( $doc->createTextNode( $this->title ) );
			$channel->appendChild( $title );
		}
		if( !empty( $this->link ) )
		{
			$link = $doc->createElement( 'link' );
			$link->appendChild( $doc->createTextNode( $this->link ) );
			$channel->appendChild( $link );
		}
		if( !empty( $this->description ) )
		{
			$description = $doc->createElement( 'description' );
			$description->appendChild( $doc->createTextNode( $this->description ) );
			$channel->appendChild( $description );
		}

		foreach( $this->items as $item )
		{
			$itemNode = $doc->createElement( 'item' );
			$channel->appendChild( $itemNode );

			$itemTitle = $doc->createElement( 'title' );
			$itemTitle->appendChild( $doc->createTextNode( $item->getTitle() ) );
			$itemNode->appendChild( $itemTitle );

			$itemLink = $doc->createElement( 'link' );
			$itemLink->appendChild( $doc->createTextNode( $item->getLink() ) );
			$itemNode->appendChild( $itemLink );

			if( !empty( $item->getDescription() ) )
			{
				$itemDescription = $doc->createElement( 'description' );
				$itemDescription->appendChild( $doc->createCdataSection( $item->getDescription() ) );
				$itemNode->appendChild( $itemDescription );
			}
			if( !empty( $item->getPubDate() ) ) // date( 'r' )
			{
				$itemPubDate = $doc->createElement( 'pubDate' );
				$itemPubDate->appendChild( $doc->createCdataSection( $item->getPubDate() ) );
				$itemNode->appendChild( $itemPubDate );
			}
		}

		return $doc->saveXml();
	}
}

