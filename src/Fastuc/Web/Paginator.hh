<?hh
namespace Fastuc\Web;

class Paginator 
{
	const PLACEHOLDER = '___PAGE___';

	/**
	 * @var integer
	 */
	private int $numItems;

	/**
	 * @var integer
	 */
	private int $itemsPerPage;

	/**
	 * @var string
	 */
	private string $urlTemplate;

	/**
	 * @var integer
	 */
	private int $selectedPage;

	public function __construct()
	{
		$this->numItems = 0;
		$this->selectedPage = 0;
		$this->itemsPerPage = 10;

		if( isset( $_SERVER['QUERY_STRING'] ) )
		{
			$this->urlTemplate = $_SERVER['QUERY_STRING'] . '&page=' . self::PLACEHOLDER;
		}
		else
		{
			$this->urlTemplate = '?page=' . self::PLACEHOLDER;
		}
	}

	/**
	 * @param string $urlTemplate
	 */
	public function setUrlTemplate( string $urlTemplate ) : void
	{
		$this->urlTemplate = $urlTemplate;
	}

	/**
	 * @param integer $numItems
	 */
	public function setNumItems( int $numItems ) : void
	{
		$this->numItems = $numItems;
	}

	/**
	 * @return integer
	 */
	public function getNumItems() : int
	{
		return $this->numItems;
	}

	/**
	 * @param integer $itemsPerPage
	 */
	public function setItemsPerPage( int $itemsPerPage ) : void
	{
		if( $itemsPerPage == 0 )
		{
			throw new \InvalidArgumentException( 'Argument can not be 0' );
		}

		$this->itemsPerPage = $itemsPerPage;
	}

	/**
	 * @return integer
	 */
	public function getNumPages() : int
	{
		return intval( ceil( $this->numItems / $this->itemsPerPage ) );
	}

	/**
	 * @param integer $number
	 */
	public function setSelectedPage( int $number ) : void
	{
		$this->selectedPage = $number;
	}

	/**
	 * @return integer
	 */
	public function getSelectedPage() : int
	{
		return $this->selectedPage;
	}

	/**
	 * @param integer $limit
	 * @return array
	 */
	public function getPages( int $limit = 10 ) : Vector<array>
	{
		$selectedPage = $this->getSelectedPage();

		$pages = new Vector<array>;
		for( $i = 0; $i < $this->getNumPages(); $i++ )
		{
			$pages->add( array(
				'url' => $this->createPageUrl( $i ),
				'number' => ( $i + 1 ),
				'selected' => ( $i == $selectedPage )
			) );
		}
		if( null !== $limit && $pages->count() > 10 )
		{
			$pages->splice( max( 0, $selectedPage - 4 ), 10 );
			if( $pages->count() < 10 )
			{
				array_unshift( $pages,
					array( 'url' => $this->createPageUrl( 0 ), 'number' => 1, 'selected' => false ),
					array( 'url' => '#', 'number' => '...', 'selected' => false )
				);
			}
		}
		return $pages;
	}

	/**
	 * @param integer $pageNumber
	 * @return string
	 */
	public function createPageUrl( int $pageNumber ) : string
	{
		return str_replace( self::PLACEHOLDER, $pageNumber, $this->urlTemplate );
	}

	/**
	 * @return bool
	 */
	public function hasPreviousPage() : bool
	{
		return ( $this->getSelectedPage() > 0 );
	}

	/**
	 * @return bool
	 */
	public function hasNextPage() : bool
	{
		return ( $this->getSelectedPage() + 1 < $this->getNumPages() );
	}

	/**
	 * @return string
	 */
	public function getPreviousPageUrl() : string
	{
		return $this->createPageUrl( $this->getSelectedPage() - 1 );
	}

	/**
	 * @return string
	 */
	public function getNextPageUrl() : string
	{
		return $this->createPageUrl( $this->getSelectedPage() + 1 );
	}
}

